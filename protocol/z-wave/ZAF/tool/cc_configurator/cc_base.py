from abc import ABC, abstractmethod
from typing import Any, Dict, List
from jinja2 import Environment, FileSystemLoader


class cc_data():
    """Command Class Data Class

    This class is responsible for containing the template file data and the file name
    It is up to the caller to use the data
    """

    def __init__(self, name: str, data: str) -> None:
        """_summary_

        Args:
            name (str): File name
            data (str): File data
        """
        self.name = name
        self.data = data


class cc_base():
    """Command Class Base class

    This class is responsible for rendering a template file
    """

    def __init__(self, component: str, templates: List[str], variable: str) -> None:
        """Constructor

        Args:
            component (str): The component name
            templates (List[str]): A list of templates, jinja files
            variable (str): The variable name used as key for the configuration
        """
        self.component = component
        self.templates = templates
        self.variable = variable

    def _render_template(self, template_file: str, templates_dir: str, **kwargs: Any) -> cc_data:
        """Render a template into a file

        Args:
            template_file (str): The template file, jinja file
            templates_dir (str): The directory in which the template is located
            output_dir (str): The output directory to which the generate file is written

        Returns:
            cc_data: Command Class data
        """
        file_loader = FileSystemLoader(templates_dir)
        env = Environment(loader=file_loader,
                          lstrip_blocks=True, trim_blocks=True)
        template = env.get_template(template_file)
        config_data = template.render(kwargs)

        c_file = template_file.replace('.jinja', '')

        return cc_data(c_file, config_data)

    def render(self, configuration: Dict[str, Dict[str, Any]], templates_dir: str) -> List[cc_data]:
        """Render all templates into files

        Args:
            configuration (Dict[str, Dict[str, Any]]): The cc_config content
            templates_dir (str): The directory in which the templates are located

        Returns:
            List[cc_data]: A list of Command Class data
        """
        ret = []
        for template in self.templates:
            ret.append(self._render_template(template, templates_dir, **{
                self.variable: configuration[self.component][self.variable]
            }))

        return ret


class cc_validate(cc_base, ABC):
    """Command Class Validate class

    This class is responsible for rendering a template file while performing
    validations to it
    """
    @abstractmethod
    def _validate(self, configuration: Dict[str, Dict[str, Any]]) -> None:
        """Abstract method

        It must be implemented by the child class else an exception is thrown

        Args:
            configuration (Dict[str, Dict[str, Any]]): The cc_config content

        Raises:
            NotImplementedError: Throws it when not implemented
        """
        raise NotImplementedError()

    def render(self, configuration: Dict[str, Dict[str, Any]], templates_dir: str) -> List[cc_data]:
        """Render all templates into files

        Args:
            configuration (Dict[str, Dict[str, Any]]): The cc_config content
            templates_dir (str): The directory in which the templates are located

        Returns:
            List[cc_data]: A list of Command Class data
        """
        self._validate(configuration)
        return super().render(configuration, templates_dir)
